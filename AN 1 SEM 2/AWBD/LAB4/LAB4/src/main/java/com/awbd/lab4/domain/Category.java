package com.awbd.lab4.domain;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Data
@Entity
public class Category {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;

    @ManyToMany(mappedBy = "categories",
            cascade = {CascadeType.PERSIST, CascadeType.MERGE})
    private List<Product> products;


}
