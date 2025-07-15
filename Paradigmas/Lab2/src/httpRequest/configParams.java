package httpRequest;

public class configParams {
    
    private String url;
    private String param;
    private String type;

    public configParams(String url, String param, String type){
        super();
        this.url = url;
        this.param = param;
        this.type = type;
    }

    public String getConfigUrl(){
        return url;
    }

    public String getConfigParam(){
        return param;
    }

    public String getConfigType(){
        return type;
    }

    public void setConfigUrl(String url){
        this.url = url;
    }

    public void setConfigParam(String param){
        this.param = param;
    }

    public void setConfigType(String type){
        this.type = type;
    }
}
