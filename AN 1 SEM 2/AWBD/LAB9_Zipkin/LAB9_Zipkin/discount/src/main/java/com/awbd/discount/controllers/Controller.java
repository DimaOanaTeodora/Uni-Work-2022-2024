package com.awbd.discount.controllers;

import com.awbd.discount.config.PropertiesConfig;
import com.awbd.discount.model.Discount;
import lombok.extern.slf4j.Slf4j;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestHeader;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Slf4j
public class Controller {
    @Autowired
    private PropertiesConfig configuration;
    private static final Logger logger = LoggerFactory.getLogger(Controller.class);
    @Autowired
    Environment environment;


    @GetMapping("/discount")
    public Discount getDiscount(){
        logger.info("get disount ....");
        return new Discount(configuration.getMonth(),configuration.getYear(), environment.getProperty("info.app.version"));
    }
}
