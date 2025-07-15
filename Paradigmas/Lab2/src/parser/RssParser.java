package parser;

import feed.Article;
import java.io.File;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;


/* Esta clase implementa el parser de feed de tipo rss (xml)
 * https://www.tutorialspoint.com/java_xml/java_dom_parse_document.htm 
 * */

public class RssParser extends GeneralParser<Article> {
    
    @Override
    public List<Article> parse(String filePath) {

        List<Article> feedlist = new ArrayList<>();

        try{
            //esta es una herramienta para leer el documento xml
            DocumentBuilderFactory factory =DocumentBuilderFactory.newInstance();
            DocumentBuilder docBuilder = factory.newDocumentBuilder();
            
            //leer el archivo xml
            File xmlFile = new File(filePath);

            //despues tenemos que analizar el documento con lo que habiamos hecho antes de doc builder
            Document xmldoc = docBuilder.parse(xmlFile);

            // normalizamos el documento XML (stack overflow: 
            //Parsers will often return "surprising" text nodes, where text is split up into 
            //multiple nodes, or, less commonly, empty text nodes. )
            xmldoc.getDocumentElement().normalize();

            // como todos los componentes del doc son items con nombre, fecha etc, los ponemos en una lista
            // donde cada nodo va a tener titulo, descripcion, publicacion y link
            NodeList itemList = xmldoc.getElementsByTagName("item");

            // Iterar sobre cada <item>
            for (int i = 0; i < itemList.getLength(); i++) {
                Node itemNode = itemList.item(i);

                if (itemNode.getNodeType() == Node.ELEMENT_NODE) {
                    Element elem = (Element) itemNode;
                    String title = elem.getElementsByTagName("title").item(0).getTextContent();
                    String link = elem.getElementsByTagName("link").item(0).getTextContent();
                    String description = elem.getElementsByTagName("description").item(0).getTextContent();

                    String pubDateStr = elem.getElementsByTagName("pubDate").item(0).getTextContent();
                    SimpleDateFormat formatter = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss Z", Locale.ENGLISH);
                    Date pubDate = formatter.parse(pubDateStr);

                    Article temp = new Article(title, description, pubDate, link);

                    feedlist.add(temp);
                }
            }

        }
        catch (Exception e) {
            e.printStackTrace();
        }

        return feedlist;
    }
}
