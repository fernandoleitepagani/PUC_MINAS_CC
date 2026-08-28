package com.example.WeatherRestAPI.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.PathVariable;

import com.example.WeatherRestAPI.service.WeatherService;

@RestController
public class controller {

    private final WeatherService service;

    public controller(WeatherService service) {
        this.service = service;
    }

    @GetMapping("/climaBH")
    public String consultarClimaBH(){
        return service.consultarClimaBH();
    }
    @GetMapping("/clima/{cidade}")
    public String consultarClima(@PathVariable String cidade){
        return service.consultarClima(cidade);
    }
}
