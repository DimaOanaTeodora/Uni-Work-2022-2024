package com.awbd.lab6.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import org.bson.types.ObjectId;
import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;
import org.springframework.data.mongodb.core.mapping.DocumentReference;
import org.springframework.data.mongodb.core.mapping.Field;

import java.util.Date;

@Setter
@Getter
@ToString
@Document(collection = "comments")
public class Comment {

    @Id
    public ObjectId id;

    private String name;
    private String email;
    private String text;
    private Date date;


    @Field("movie_id")
    private ObjectId movieId;
}
