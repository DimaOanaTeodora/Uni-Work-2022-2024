package com.awbd.lab4.services;

import com.awbd.lab4.domain.Product;
import com.awbd.lab4.repositories.ProductRepository;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.data.domain.Sort;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
public class ProductServiceTest {
    @Mock
    ProductRepository productRepository;

    @InjectMocks
    ProductServiceImpl productService;

    @Test
    public void findProducts() {
        List<Product> productsRet = new ArrayList<Product>();
        Product product = new Product();
        product.setId(4L);
        product.setCode("TEST");
        productsRet.add(product);

        when(productRepository.findAll(Sort.by("name"))).thenReturn(productsRet);
        List<Product> products = productService.findAll();
        assertEquals(products.size(), 1);
        verify(productRepository, times(1)).findAll(Sort.by("name"));
    }


}
