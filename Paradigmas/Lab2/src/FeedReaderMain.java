
import parser.SubscriptionParser;
import subscription.SingleSubscription;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import feed.Article;

import java.io.FileWriter;
import java.io.IOException;

import httpRequest.httpRequester;
import httpRequest.configParams;

import parser.RssParser;

import namedEntity.heuristic.Heuristic;
import namedEntity.heuristic.QuickHeuristic;
import namedEntity.heuristic.RandomHeuristic;
import namedEntity.NamedEntity;

public class FeedReaderMain {

	// Colores
	public static final String ANSI_CYAN = "\u001B[36m";

	private static void printHelp() {
		System.out.println("Please, call this program in correct way: FeedReader [-ne]");
	}

	/**
	 * Método para obtener la lista con URLs finales
	 * 
	 * @param subs List de SingleSubscription.
	 * @return List de list de String con cada URL "final".
	 */
	private static List<configParams> listConfig(List<SingleSubscription> subs) {
		List<configParams> res = new ArrayList<>();

		for (int i = 0; i < subs.size(); i++) {
			SingleSubscription sub = subs.get(i);

			for (int j = 0; j < sub.getUrlParamsSize(); j++) {
				String urlFinal = sub.getUrl().replace("%s", sub.getUrlParams(j));
				String param = sub.getUrlParams(j);
				String type = sub.getUrlType();

				configParams configs = new configParams(urlFinal, param, type);

				res.add(configs);
			}
		}
		return res;
	}

	private static List<Article> getArticleList() {
		List<Article> articleList = new ArrayList<>();

		SubscriptionParser parser = new SubscriptionParser();

		List<SingleSubscription> subs = parser.parse("config/subscriptions.json");

		List<configParams> configs = listConfig(subs);

		httpRequester requester = new httpRequester();

		// Guardamos el contenido en un .xml
		for (int i = 0; i < configs.size(); i++) {
			configParams temp = configs.get(i);

			String url = temp.getConfigUrl();
			String param = temp.getConfigParam();
			String type = temp.getConfigType();

			String contenido = requester.getHttp(url);

			try {
				FileWriter file = new FileWriter("config/" + param + "_" + type + ".xml");
				file.write(contenido);
				file.close();
			} catch (IOException e) {
				System.out.println("Error en FileWriter");
			}
		}

		RssParser rss = new RssParser();

		for (int i = 0; i < configs.size(); i++) {
			String type = "rss";
			configParams temp = configs.get(i);

			if (type.equals(temp.getConfigType())) {

				String path = "config/" + temp.getConfigParam() + "_" + temp.getConfigType() + ".xml";
				List<Article> articlesList = rss.parse(path);
				return articlesList;
			}
		}
		return articleList;
	}

	private static void wordRunner(String[] array, QuickHeuristic entity, Map<String, NamedEntity> entityMap){
		for (int i = 0; i < array.length; i++) {
						
			String word = array[i];
			boolean wordIsEntity = false;

			if (!word.matches(".*\\d.*") && !word.isEmpty()) {
				wordIsEntity = entity.isEntity(word);
			}

			if (wordIsEntity) {
				if (wordIsEntity) { // Entra si es entidad

					String category = entity.getCategory(word);

					if (category == null) {
						category = "Other";
					}

					NamedEntity existing = entityMap.get(word); // Busca la palabra en el map
					NamedEntity catExist = entityMap.get(category);

					// Sino existe la crea y si existe incrementa la frecuencia
					if (existing == null) {
						NamedEntity temp = new NamedEntity(word, category, 1);
						entityMap.put(word, temp);
					} else {
						existing.incFrequency();
					}

					if (catExist == null) {
						NamedEntity temp = new NamedEntity(category, "category", 1);
						entityMap.put(category, temp);
					} else {
						catExist.incFrequency();
					}
				}
			}
		}
	}

	public static void main(String[] args) {
		System.out.println("************* FeedReader version 1.0 *************");
		List<Article> articleList = getArticleList();

		if (args.length == 0) {

			for (int j = 0; j < articleList.size(); j++) {
				articleList.get(j).prettyPrint();
			}

		} else if (args.length == 1) {
			/*
			 * Leer el archivo de suscription por defecto;
			 * Llamar al httpRequester para obtenr el feed del servidor
			 * Llamar al Parser especifico para extrar los datos necesarios por la
			 * aplicacion
			 * Llamar al constructor de Feed
			 * Llamar a la heuristica para que compute las entidades nombradas de cada
			 * articulos del feed
			 * LLamar al prettyPrint de la tabla de entidades nombradas del feed.
			 */

			String arg = args[0];

			if (arg.equals("-ne")) {

				// Mapa de las entidades
				Map<String, NamedEntity> entityMap = new HashMap<>();

				// Recorrer cada articulo
				for (int j = 0; j < articleList.size(); j++) {
					String tempTitle = articleList.get(j).getTitle();
					String tempText = articleList.get(j).getText();
					String[] titleArray = tempTitle.split("[^a-zA-ZáéíóúÁÉÍÓÚñÑ]+");
					String[] textArray = tempText.split("[^a-zA-ZáéíóúÁÉÍÓÚñÑ]+");
					QuickHeuristic titleh = new QuickHeuristic();
					QuickHeuristic texth = new QuickHeuristic();

					// Recorrer las palabras del titulo
					wordRunner(titleArray, titleh, entityMap);
					// Recorrer las palabras del texto
					wordRunner(textArray, texth, entityMap);
				}

				// printf
				for (NamedEntity entity : entityMap.values()) {
					entity.prettyPrint();
				}


			}

		} else {
			printHelp();
		}
	}

}
