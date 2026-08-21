package com.example.RestApi;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Controller {

    @GetMapping("/test")
    public String helloword(){
        return "Essa é minha primeira API REST";
    }
    @GetMapping("/diaw")
	public String diaw() {
        return "Esse é meu segundo endpoint";
	}
}
