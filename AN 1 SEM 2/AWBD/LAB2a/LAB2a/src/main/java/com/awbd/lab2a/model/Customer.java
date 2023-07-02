package com.awbd.lab2a.model;

import lombok.*;



@Setter
@Getter
@Builder
@AllArgsConstructor
public class Customer {
    public Customer(){};
    private Long id;
    private String firstName;
    private String lastName;
    private String email;


}
