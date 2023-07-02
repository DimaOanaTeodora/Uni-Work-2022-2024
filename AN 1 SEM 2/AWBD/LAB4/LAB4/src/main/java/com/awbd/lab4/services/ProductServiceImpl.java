package com.awbd.lab4.services;

import com.awbd.lab4.domain.Category;
import com.awbd.lab4.domain.Product;
import com.awbd.lab4.repositories.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;

@Service
public class ProductServiceImpl implements ProductService {
    ProductRepository productRepository;

    @Autowired
    public ProductServiceImpl(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    @Override
    public List<Product> findAll(){
        List<Product> products = new LinkedList<>();
        productRepository.findAll(Sort.by("name")).iterator().forEachRemaining(products::add);
        return products;
    }

    @Override
    public Product findById(Long l) {
        Optional<Product> productOptional = productRepository.findById(l);
        if (!productOptional.isPresent()) {
            throw new RuntimeException("Product not found!");
        }
        return productOptional.get();
    }

    @Override
    public Product save(Product product) {
        Product savedProduct = productRepository.save(product);
        return savedProduct;
    }

    @Override
    public void deleteById(Long id) {

        Optional<Product> productOptional = productRepository.findById(id);
        if (!productOptional.isPresent()) {
            throw new RuntimeException("Product not found!");
        }
        Product product = productOptional.get();
        List<Category> categories = new LinkedList<Category>();
        product.getCategories().iterator().forEachRemaining(categories::add);
        categories.iterator().forEachRemaining(product::removeCategory);

        productRepository.save(product);
        productRepository.deleteById(id);

    }
}
