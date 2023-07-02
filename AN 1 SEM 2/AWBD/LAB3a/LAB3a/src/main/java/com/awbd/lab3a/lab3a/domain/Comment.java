package com.awbd.lab3a.lab3a.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.Date;

@Setter
@Getter
@ToString
public class Comment {

    private String id;

    private String name;
    private String email;
    private String text;
    private Date date;
}
