package com.awbd.lab4.domain;

import jakarta.persistence.*;
import lombok.Data;

import java.util.List;

@Data
@Entity
public class Participant {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String lastName;
    private String firstName;
    private java.util.Date birthDate;

    @OneToMany(mappedBy = "seller", cascade = CascadeType.ALL)
    private List<Product> products;





}
