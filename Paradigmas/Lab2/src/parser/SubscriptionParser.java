package parser;

import org.json.JSONArray;
import org.json.JSONObject;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import subscription.SingleSubscription;

public class SubscriptionParser extends GeneralParser<SingleSubscription> {

    /**
    * Método para parsear una subscripcion
    * @param filePath Ruta al archivo a parsear
    * @return Lista de objetos del tipo SingleSubscription
    */
    @Override
    public List<SingleSubscription> parse(String filePath) {

        List<SingleSubscription> subscriptions = new ArrayList<>();

        try {

            // Lee todo el contenido y lo guarda en un string
            String content = new String(Files.readAllBytes(Paths.get(filePath)));
            // Convierte el string en un JSONArray
            JSONArray array = new JSONArray(content);

            for (int i = 0; i < array.length(); i++) {
                JSONObject obj = array.getJSONObject(i);

                // Obtengo el url
                String url = obj.getString("url");
                
                // Obtengo urlParams y lo convierto en List<String>
                JSONArray params = obj.getJSONArray("urlParams");
                
                List<String> paramList = new ArrayList<>();
                for (int j = 0; j < params.length(); j++) {
                    String param = params.getString(j);
                    paramList.add(param);
                }
                
                // Obtengo urlType
                String urlType = obj.getString("urlType");
                
                SingleSubscription singleSub = new SingleSubscription(url, paramList, urlType);

                subscriptions.add(singleSub);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return subscriptions;
    }
}
