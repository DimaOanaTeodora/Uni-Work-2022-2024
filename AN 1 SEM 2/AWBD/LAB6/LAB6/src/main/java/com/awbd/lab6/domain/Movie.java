package com.awbd.lab6.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import org.bson.types.ObjectId;
import org.springframework.data.annotation.Id;
import org.springframework.data.annotation.ReadOnlyProperty;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.DocumentReference;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Field;

import java.util.*;

@Setter
@Getter
@ToString
@Document(collection = "movies")
public class Movie {

    @Id
    public ObjectId id;
    private String title;
    private String plot;
    private Date released;
    private List<String> cast;
    private String year;
    private Imdb imdb;

    @ReadOnlyProperty
    @DocumentReference(lookup="{'movie_id':?#{#self._id} }")
    private List<Comment> comments = new ArrayList<>();

}

