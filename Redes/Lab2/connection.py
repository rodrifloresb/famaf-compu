# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Copyright 2014 Carlos Bederián
# $Id: connection.py 455 2011-05-01 00:32:09Z carlos $

import socket
import os
from constants import *
from base64 import b64encode

class Connection(object):
    """
    Conexión punto a punto entre el servidor y un cliente.
    Se encarga de satisfacer los pedidos del cliente hasta
    que termina la conexión.
    """

    def __init__(self, socket, directory):
        # Inicializar atributos de Connection
        self.socket = socket
        self.directory = directory
        
        self.connect = True

    def handle(self):
        """
        Atiende eventos de la conexión hasta que termina.
        """
        buffer = ''
                
        while self.connect:
            # Completar
            try:
                data = self.socket.recv(MAX_SIZE).decode('ascii')
                if data:
                    buffer += data
                    
                    # en client.py se completa con fin de linea
                    while EOL in buffer:
                        message, buffer = buffer.split(EOL, 1)

                        # Se encontró un carácter \n fuera de un terminador de pedido \r\n.
                        if '\n' in message:
                            response = f"{BAD_EOL} {error_messages[BAD_EOL]}"
                            response += f"{EOL}"
                            self.socket.send(response.encode('ascii'))
                            self.connect = False
                            break
                        
                        command = message.split()[0]
                        args = message.split()[1:]
                        print(f"Request: {message}")

                        if command == 'get_file_listing':
                            self.handle_get_file_listing(args)
                        
                        elif command == 'get_metadata':
                            self.handle_get_metadata(args)
                            
                        elif command == 'get_slice':
                            self.handle_get_slice(args)
                            
                        elif command == 'quit':
                            self.handle_quit(args)
                            
                        else:
                            response = f"{INVALID_COMMAND} "
                            response += f"{error_messages[INVALID_COMMAND]}"
                            response += f"{EOL}"
                            self.socket.send(response.encode('ascii'))
                else:
                    self.connect = False
                    break
            
            # El servidor tuvo algún fallo interno 
            # al intentar procesar el pedido.
            except:
                response = f"{INTERNAL_ERROR} "
                response += f"{error_messages[INTERNAL_ERROR]}{EOL}"
                self.socket.send(response.encode('ascii'))
                self.connect = False
                break
        self.socket.close()
        print("Closing connection...")

    def handle_get_file_listing(self, args):
        """
        os.listdir(dir)     Devuelve archivos y carpetas en dir
        os.path.isfile()    Comprueba si es un archivo 
                            (No queremos devolver carpetas)

        os.path.join(dir)   Coloca / \ dependiendo del SO
        """

        if self.invalid_args(args, 0):
            return   

        filenames = [   
            f for f in os.listdir(self.directory)
            if os.path.isfile(os.path.join(self.directory, f))
        ]

        response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}"
        self.socket.send(response.encode('ascii'))

        for name in filenames:
            response = f"{name}{EOL}"
            self.socket.send(response.encode('ascii'))

        self.socket.send(EOL.encode('ascii'))


    def handle_get_slice(self, args):
        #validacion de cantidad de argumentos
        if self.invalid_args(args, 3):
            return
        
        #separa los 3 argumentos
        filename, offset_str, size_str = args 

        #validacion de que offset y size son numeros
        if not offset_str.isdigit() or not size_str.isdigit():
            response = f"{INVALID_ARGUMENTS} "
            response += f"{error_messages[INVALID_ARGUMENTS]}{EOL}"
            self.socket.send(response.encode('ascii'))
            return 
        
        #convertir offset y size a enteros (porq los necesito como num para leer el archivo)
        offset = int(offset_str)
        size = int(size_str)

        #concatenar el dir base del servidor con el nombre del archivo pedido
        filepath = os.path.join(self.directory, filename)

        #verif q el archivo existe
        if not os.path.isfile(filepath):
            response = f"{FILE_NOT_FOUND} {error_messages[FILE_NOT_FOUND]}"
            response += f"{EOL}"
            self.socket.send(response.encode('ascii'))
            return
        
        #CASO BORDE
        #ver que el offset no sea mayor que el tamaño del archivo
        file_size = os.path.getsize(filepath)
        if offset + size > file_size:
            response = f"{BAD_OFFSET} {error_messages[BAD_OFFSET]}{EOL}"
            self.socket.send(response.encode('ascii'))
            return
        
        #abro el archivo en modo binario
        with open(filepath, 'rb') as f: 
            f.seek(offset) #va al byte indicado
            chunk = f.read(size) #lee la cantidad pedida de bytes
        
        #codificar en base64
        encoded = b64encode(chunk).decode('ascii')
        #enviar el 0 OK\r\n si todo salio bien 
        response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}"
        self.socket.send(response.encode('ascii'))

        #finalmente se mandan los datos codificados
        self.socket.send((f"{encoded}{EOL}").encode('ascii'))
        
        
    def handle_get_metadata(self, args):
        if self.invalid_args(args, 1):
            return

        filename = args[0]

        file_path = os.path.join(self.directory, filename) 

        if not os.path.isfile(file_path):
            response = f"{FILE_NOT_FOUND} {error_messages[FILE_NOT_FOUND]}"
            response += f"{EOL}"
            self.socket.send(response.encode('ascii'))
            return
        # devuelve el tam de un archivo en bytes
        file_size = os.path.getsize(file_path) 
        response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}{file_size}{EOL}"
        self.socket.send(response.encode('ascii'))
        
        
    def handle_quit(self, args):
        if self.invalid_args(args, 0):
            return
        response = f"{CODE_OK} {error_messages[CODE_OK]}{EOL}"
        self.socket.send(response.encode('ascii'))
        self.connect = False

    def invalid_args(self, args, size):
        if len(args) != size:
            response = f"{INVALID_ARGUMENTS} "
            response += f"{error_messages[INVALID_ARGUMENTS]}{EOL}"
            self.socket.send(response.encode('ascii'))
            return True
        return False
    

    