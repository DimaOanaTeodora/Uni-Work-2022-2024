package com.awbd.lab4.services;

import com.awbd.lab4.domain.Category;
import com.awbd.lab4.repositories.CategoryRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.LinkedList;
import java.util.List;

@Service
public class CategoryServiceImpl implements CategoryService{

    CategoryRepository categoryRepository;

    @Autowired
    public CategoryServiceImpl(CategoryRepository categoryRepository) {
        this.categoryRepository = categoryRepository;
    }

    @Override
    public List<Category> findAll() {
        List<Category> categories = new LinkedList<>();
        categoryRepository.findAll().iterator().forEachRemaining(categories
                ::add);
        return categories ;
    }
}
