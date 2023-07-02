package com.awbd.lab4.controllers;

import com.awbd.lab4.domain.Category;
import com.awbd.lab4.domain.Info;
import com.awbd.lab4.domain.Product;
import com.awbd.lab4.services.CategoryService;
import com.awbd.lab4.services.PhotoService;
import com.awbd.lab4.services.ProductService;
import org.apache.tomcat.util.http.fileupload.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;


@Controller
@RequestMapping("/products")
public class ProductController {
    ProductService productService;

    @Autowired
    CategoryService categoryService;

    @Autowired
    PhotoService photoService;

    @Autowired
    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    /*
    @RequestMapping("")
    public String productList(Model model) {
        List<Product> products = productService.findAll();
        model.addAttribute("products",products);
        return "productList";
    }*/


    @RequestMapping("")
    public ModelAndView products(){
        ModelAndView modelAndView = new ModelAndView("productList");
        List<Product> products = productService.findAll();
        modelAndView.addObject("products",products);
        return modelAndView;
    }


    @GetMapping("/{id}")
    public String getById(@PathVariable String id, Model model){

        Product product = productService.findById(Long.valueOf(id));
        model.addAttribute("product",
                product);
        return "productDetails";
    }

    @RequestMapping("/delete/{id}")
    public String deleteById(@PathVariable String id){
        productService.deleteById(Long.valueOf(id));
        return "redirect:/products";
    }


    @RequestMapping("/form")
    public String productForm(Model model) {
        model.addAttribute("product", new Product());
        List<Category> categoriesAll = categoryService.findAll();
        model.addAttribute("categoriesAll", categoriesAll );
        return "productform";
    }


    @PostMapping("")
    public String saveOrUpdate(@ModelAttribute Product product,
                               @RequestParam("imagefile") MultipartFile file
    ){
        Product savedProduct;
        if (file.isEmpty())
            savedProduct = productService.save(product);
        else
            photoService.savePhotoFile(product, file);

        return "redirect:/products" ;
    }


    @RequestMapping("/edit/{id}")
    public String edit(@PathVariable String id, Model model) {
        model.addAttribute("product",
                productService.findById(Long.valueOf(id)));

        List<Category> categoriesAll = categoryService.findAll();
        model.addAttribute("categoriesAll", categoriesAll );

        return "productForm";
    }
}