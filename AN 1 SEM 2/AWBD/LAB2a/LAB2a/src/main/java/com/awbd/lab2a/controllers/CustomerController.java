package com.awbd.lab2a.controllers;


import com.awbd.lab2a.configuration.Log;
import com.awbd.lab2a.model.Customer;
import com.awbd.lab2a.service.CustomerService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import java.util.List;

@Controller
@RequestMapping("/customers")
public class CustomerController {


    CustomerService customerService;


    @Autowired
    public CustomerController(CustomerService customerService) {

        this.customerService = customerService;
    }

    /*    @RequestMapping("")
    public String productsList(Model model){
        List<Product> customers = customerService.findAll();
        model.addAttribute("customers",customers);

        return "products";
    }*/
    @Log
    @RequestMapping("")
    public ModelAndView products(){
        ModelAndView modelAndView = new ModelAndView("customers");
        List<Customer> customers = customerService.findAll();

        customerService.save(customers.get(0));

        modelAndView.addObject("customers",customers);
        return modelAndView;
    }

}
