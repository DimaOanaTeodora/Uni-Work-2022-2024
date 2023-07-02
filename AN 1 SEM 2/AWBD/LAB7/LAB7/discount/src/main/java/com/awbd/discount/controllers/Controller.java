package com.awbd.discount.controllers;

import com.awbd.discount.config.PropertiesConfig;
import com.awbd.discount.model.Discount;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Controller {
    @Autowired
    private PropertiesConfig configuration;

    @GetMapping("/discount")
    public Discount getDiscount(){
        return new Discount(configuration.getMonth(),configuration.getYear());
    }
}
