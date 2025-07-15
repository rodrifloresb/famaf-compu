#!/usr/bin/env python
# encoding: utf-8
# Revisión 2019 (a Python 3 y base64): Pablo Ventura
# Revisión 2014 Carlos Bederián
# Revisión 2011 Nicolás Wolovick
# Copyright 2008-2010 Natalia Bidart y Daniel Moisset
# $Id: server.py 656 2013-03-18 23:49:11Z bc $

import optparse
import socket
import connection
import sys
import threading
from constants import *


class Server(object):
    """
    El servidor, que crea y atiende el socket en la dirección y puerto
    especificados donde se reciben nuevas conexiones de clientes.
    """

    def __init__(self, addr=DEFAULT_ADDR, port=DEFAULT_PORT,
                 directory=DEFAULT_DIR):
        print("Serving %s on %s:%s." % (directory, addr, port))
        # Crear socket del servidor, configurarlo, asignarlo
        # a una dirección y puerto, etc.

        # Creoamos un socket TCP
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        #Reutilizamos la direccion si esta en TIME_WAIT
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        #Lo asociamos a la direccion y el puerto 
        self.sock.bind((addr, port))

        #lo ponemos a escuchar (hasta 5 conexiones en cola)
        self.sock.listen(5)

        #guardamos el directorio para usar en Connection 
        self.directory = directory

    def serve(self):
        """
        Loop principal del servidor. Se acepta una conexión a la vez
        y se espera a que concluya antes de seguir.
        """
        while True:
            try:
            # Aceptar una conexión al server, crear una
            # Connection para la conexión y atenderla hasta que termine.
                #espera y acepta una nueva conexion entrante
                client_socket, addr = self.sock.accept()
                print("Connected by:", addr)

                #crea una instancia de connection con el socket del cliente
                conn = connection.Connection(client_socket, self.directory)

                #crea y lanza un hilo para manejar la conexion
                thread = threading.Thread(target=conn.handle) 
                thread.start()

            except KeyboardInterrupt: 
                print("\n[INFO] Servidor detenido por el usuario.")
                break

            except Exception as e: 
                print(f"[ERROR] Error atendiendo la conexion: {e}")


def main():
    """Parsea los argumentos y lanza el server"""

    parser = optparse.OptionParser()
    parser.add_option(
        "-p", "--port",
        help="Número de puerto TCP donde escuchar", default=DEFAULT_PORT)
    parser.add_option(
        "-a", "--address",
        help="Dirección donde escuchar", default=DEFAULT_ADDR)
    parser.add_option(
        "-d", "--datadir",
        help="Directorio compartido", default=DEFAULT_DIR)

    options, args = parser.parse_args()
    if len(args) > 0:
        parser.print_help()
        sys.exit(1)
    try:
        port = int(options.port)
    except ValueError:
        sys.stderr.write(
            "Numero de puerto invalido: %s\n" % repr(options.port))
        parser.print_help()
        sys.exit(1)

    server = Server(options.address, port, options.datadir)
    server.serve()


if __name__ == '__main__':
    main()
