package com.awbd.lab4.domain;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
@Entity
public class Info {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Lob
    @Column(name = "photo", columnDefinition="BLOB")
    private Byte[] photo;

    private String description;

    @OneToOne
    private Product product;


}
