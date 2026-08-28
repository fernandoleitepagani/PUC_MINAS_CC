package com.example.WeatherRestAPI.service;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class WeatherService{

    @Value("${openmeteo.api.url}")
    private String apiUrl;

    @Value("${bh.api.url}")
    private String apiUrlBH;

    public String consultarURL(String url) {

        RestTemplate restTemplate = new RestTemplate();
        ResponseEntity<String> responseEntity = restTemplate.getForEntity(url, String.class);

        if (responseEntity.getStatusCode().is2xxSuccessful()) {
            return responseEntity.getBody();
        } else {
            return "Falha ao obter dados meteorológicos. Código: " + responseEntity.getStatusCode();
        }
    }

    public String consultarClimaBH(){
        return consultarURL(apiUrlBH);
    }
    public String consultarClima(String cidade){
        return consultarURL(apiUrl + cidade + "&count=1&language=pt&format=json");
    }
}
