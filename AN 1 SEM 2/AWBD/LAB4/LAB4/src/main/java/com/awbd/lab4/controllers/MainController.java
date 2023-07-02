package com.awbd.lab4.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

@Controller
public class MainController {

    @RequestMapping({"","/","/auction"})
    public ModelAndView getHome(){

        return new ModelAndView("main");
    }

    @RequestMapping({"","/","/auction2"})
    public String getHome2(){

        return "test";
    }

}
