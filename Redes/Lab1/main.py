from flask import Flask, jsonify, request, json
import random # Para "pelicula_al_azar"
from proximo_feriado import NextHoliday

app = Flask(__name__)
peliculas = [
    {'id': 1, 'titulo': 'Indiana Jones', 'genero': 'Acción'},
    {'id': 2, 'titulo': 'Star Wars', 'genero': 'Acción'},
    {'id': 3, 'titulo': 'Interstellar', 'genero': 'Ciencia ficción'},
    {'id': 4, 'titulo': 'Jurassic Park', 'genero': 'Aventura'},
    {'id': 5, 'titulo': 'The Avengers', 'genero': 'Acción'},
    {'id': 6, 'titulo': 'Back to the Future', 'genero': 'Ciencia ficción'},
    {'id': 7, 'titulo': 'The Lord of the Rings', 'genero': 'Fantasía'},
    {'id': 8, 'titulo': 'The Dark Knight', 'genero': 'Acción'},
    {'id': 9, 'titulo': 'Inception', 'genero': 'Ciencia ficción'},
    {'id': 10, 'titulo': 'The Shawshank Redemption', 'genero': 'Drama'},
    {'id': 11, 'titulo': 'Pulp Fiction', 'genero': 'Crimen'},
    {'id': 12, 'titulo': 'Fight Club', 'genero': 'Drama'}
]

def normalizar(string: str) -> str:
    reemplazos = {
        'á': 'a', 'é': 'e', 'í': 'i', 'ó': 'o', 'ú': 'u',
        'Á': 'A', 'É': 'E', 'Í': 'I', 'Ó': 'O', 'Ú': 'U'
    }
    for acentuada, sin_acento in reemplazos.items():
        string = string.replace(acentuada, sin_acento)

    string = string.lower()

    return string


def obtener_peliculas() -> json:
    """Se retorna en formato JSON el array"""
    return jsonify(peliculas)


def obtener_pelicula(id: int) -> json:
    """Lógica para buscar la película por su ID 
    y devolver sus detalles"""

    pelicula_encontrada = next((elem for elem in peliculas 
                                if elem['id'] == id), 
                                None)

    if pelicula_encontrada == None:
        return jsonify({"error":"Pelicula no encontrada"}), 404

    return jsonify(pelicula_encontrada)


def agregar_pelicula() -> json:
    nueva_pelicula = {
        'id': obtener_nuevo_id(),
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }
    peliculas.append(nueva_pelicula)
    print(peliculas)
    return jsonify(nueva_pelicula), 201


def actualizar_pelicula(id: int) -> json:
    """Lógica para buscar la película por su ID 
    y actualizar sus detalles"""
    
    res = next((elem for elem in peliculas if elem['id'] == id), None)

    if res == None:
        return jsonify({"error":"Pelicula no encontrada"}), 404
    
    
    pelicula_update = {
        'id': id,
        'titulo': request.json['titulo'],
        'genero': request.json['genero']
    }

    res.update(pelicula_update)

    return jsonify(res)


def eliminar_pelicula(id: int) -> json:
    """Lógica para buscar la película por su ID y eliminarla"""

    res = next((elem for elem in peliculas if elem['id'] == id), None)

    if res == None:
        return jsonify({"error":"Pelicula no encontrada"}), 404
    
    peliculas.remove(res)

    return jsonify({'mensaje': 'Película eliminada correctamente'})

def obtener_pelicula_por_genero(genero: str) -> json:
    """Devolver el listado de peliculas de un genero especifico""" 
    peliculas_filtradas = [elem for elem in peliculas if
                           normalizar(elem['genero']) == normalizar(genero)]

    if not peliculas_filtradas: 
        return jsonify({"ERROR":
                        "No se encontraron peliculas con ese genero"}), 404
    
    return jsonify(peliculas_filtradas)


def busqueda_de_peliculas(title: str) -> json:
    """Retorna una lista de peliculas en donde su titulos
    coindicen parcialmente con 'title'"""

    peliculas_encontradas = []
    for pelicula in peliculas:
        if normalizar(title) in normalizar(pelicula['titulo']):
            peliculas_encontradas.append(pelicula)

    return jsonify(peliculas_encontradas)

def pelicula_al_azar(array: list) -> json:
    """Retorna una pelicula al azar"""

    return random.choice(array)


def pelicula_del_genero_al_azar(genero: str) -> json:
    """Retorna una pelicula al azar dentro de cierto genero"""

    temp = obtener_pelicula_por_genero(genero).get_json()

    if isinstance(temp, dict) and "ERROR" in temp:
        return jsonify(temp)

    return pelicula_al_azar(temp)


def obtener_nuevo_id() -> int:
    if len(peliculas) > 0:
        ultimo_id = peliculas[-1]['id']
        return ultimo_id + 1
    else:
        return 1
        
def pelicula_para_feriado (genero: str) -> json:
    next_holiday = NextHoliday()  # instancia de clase
    next_holiday.fetch_holidays() # fetch busca en la API los datos
    feriado = next_holiday.holiday # guardando en feriado
    peliculas_filtradas = [p for p in peliculas if normalizar(p['genero']) 
                           == normalizar(genero)]
    if not peliculas_filtradas:
        return jsonify({"ERROR":
                        "No se encontraron peliculas con ese genero"}), 404
    # se elige una pelicula al azar de la lista filtrada    
    pelicula = pelicula_al_azar(peliculas_filtradas) 
    return jsonify({
        "feriado":{
            "dia": feriado['dia'],
            "mes": feriado['mes'],
            "motivo": feriado['motivo'],
            "tipo": feriado['tipo']
        },
        "pelicula": pelicula
    })        

app.add_url_rule('/peliculas', 'obtener_peliculas', obtener_peliculas
                 , methods=['GET'])
app.add_url_rule('/peliculas/<int:id>', 'obtener_pelicula', obtener_pelicula
                 , methods=['GET'])
app.add_url_rule('/peliculas', 'agregar_pelicula', agregar_pelicula
                 , methods=['POST'])
app.add_url_rule('/peliculas/<int:id>', 'actualizar_pelicula'
                 , actualizar_pelicula, methods=['PUT'])
app.add_url_rule('/peliculas/<int:id>', 'eliminar_pelicula'
                 , eliminar_pelicula, methods=['DELETE'])
app.add_url_rule('/peliculas/genero/<string:genero>'
                 , 'obtener_pelicula_por_genero', obtener_pelicula_por_genero
                 , methods=['GET'])
app.add_url_rule('/peliculas/title/<string:title>', 'busqueda_de_peliculas'
                 , busqueda_de_peliculas, methods=['GET'])
app.add_url_rule('/peliculas/azar', 'pelicula_al_azar',
                 lambda: pelicula_al_azar(peliculas), methods=['GET'] )
app.add_url_rule('/peliculas/azar/<string:genero>',
                 'pelicula_del_genero_al_azar', pelicula_del_genero_al_azar
                 , methods=['GET'])
app.add_url_rule('/peliculas/feriado/<string:genero>'
                 , 'pelicula_para_feriado', pelicula_para_feriado
                 , methods=['GET'])



if __name__ == '__main__':
    app.run()
