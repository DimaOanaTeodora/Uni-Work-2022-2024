package com.awbd.lab4.controllers;

import com.awbd.lab4.domain.Info;
import com.awbd.lab4.domain.Product;
import com.awbd.lab4.services.PhotoService;
import com.awbd.lab4.services.ProductService;
import jakarta.servlet.http.HttpServletResponse;
import org.apache.tomcat.util.http.fileupload.IOUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;


import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

@Controller
public class ImageController {

    private final ProductService productService;


    public ImageController(@Autowired PhotoService imageService, @Autowired ProductService productService) {
        this.productService = productService;
    }

    @GetMapping("products/getimage/{id}")
    public void downloadImage(@PathVariable String id, HttpServletResponse response) throws IOException {
        Product product = productService.findById(Long.valueOf(id));
        if (product.getInfo() != null) {
            Info info = product.getInfo();

            if (product.getInfo().getPhoto() != null) {
                byte[] byteArray = new byte[info.getPhoto().length];
                int i = 0;
                for (Byte wrappedByte : info.getPhoto()) {
                    byteArray[i++] = wrappedByte;
                }
                response.setContentType("image/jpeg");
                InputStream is = new ByteArrayInputStream(byteArray);
                try {
                    IOUtils.copy(is, response.getOutputStream());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}