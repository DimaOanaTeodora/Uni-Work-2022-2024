package com.awbd.lab3.domain;

import jakarta.persistence.*;

@Entity
public class Info {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private Byte[] photo;
    private String description;

    @OneToOne
    private Product product;


}
