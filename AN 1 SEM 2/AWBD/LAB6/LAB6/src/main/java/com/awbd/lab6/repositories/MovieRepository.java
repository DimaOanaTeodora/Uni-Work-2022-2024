package com.awbd.lab6.repositories;

import com.awbd.lab6.domain.Movie;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.mongodb.repository.Query;

import java.util.List;

public interface MovieRepository extends MongoRepository<Movie, String> {
    List<Movie> findByTitle(String title);


    List<Movie> findByYearBetween(int start, int end);

    @Query("{ 'year' : { $gt: ?0, $lt: ?1 } }")
    List<Movie> findByYearBetweenQ(int start, int end);


    @Query("{ 'title' : { $regex: ?0 } }")
    List<Movie> findByTitleRegexpQ(String regexp);

}
