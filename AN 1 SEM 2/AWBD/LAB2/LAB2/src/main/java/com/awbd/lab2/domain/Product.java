package com.awbd.lab2.domain;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Data
@Entity
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String name;
    private String code;
    private Double reservePrice;
    private Boolean restored;

    @OneToOne
    private Info info;

    @ManyToOne
    private Participant seller;


    @ManyToMany(mappedBy = "products")
    private List<Category> categories;


    @Enumerated(value = EnumType.STRING)
    private Currency currency;


}
