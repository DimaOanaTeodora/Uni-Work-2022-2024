package com.awbd.lab3a.lab3a.domain;


import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.util.Date;
import java.util.List;

@Setter
@Getter
@ToString
public class Movie {

    private String id;
    private String title;
    private String plot;
    private Date released;
    private List<String> cast;
    private String year;
    private Imdb imdb;
    private List<Comment> comments;

    public Movie(String id) {
        this.id = id;
    }
}

