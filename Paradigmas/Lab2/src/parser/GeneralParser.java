package parser;

import java.util.List;

/*Esta clase modela los atributos y metodos comunes a todos los distintos tipos de parser existentes en la aplicacion*/

public abstract class GeneralParser<T> {
    /**
    * Método abstracto que deben implementar las subclases para parsear un archivo
    * @param filePath Ruta al archivo a parsear
    * @return Lista de objetos del tipo T
    */
    public abstract List<T> parse(String filePath);
}
