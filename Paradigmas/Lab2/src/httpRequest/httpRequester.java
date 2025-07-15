package httpRequest;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;


/* Esta clase se encarga de realizar efectivamente el pedido de feed al servidor de noticias
Leer sobre como hacer una http request en java
https://www.baeldung.com/java-http-request
*/



public class httpRequester {

    private static HttpClient client = HttpClient.newHttpClient();

    public String getHttp(String url) {
        try{
            HttpRequest request = HttpRequest.newBuilder(URI.create(url)).GET().build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            return response.body();
        }
        catch (Exception e){
            System.err.println("Error al conectar con la URL: " + url);
        }
        return null; 
    }

}
