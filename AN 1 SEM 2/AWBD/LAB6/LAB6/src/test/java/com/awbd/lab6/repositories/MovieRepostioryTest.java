package com.awbd.lab6.repositories;

import com.awbd.lab6.domain.Comment;
import com.awbd.lab6.domain.Movie;
import lombok.extern.slf4j.Slf4j;
import org.bson.types.ObjectId;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Optional;

import static org.junit.jupiter.api.Assertions.assertFalse;

@SpringBootTest
@Slf4j
public class MovieRepostioryTest {

    @Autowired
    MovieRepository movieRepository;

    @Autowired
    CommentRepository commentRepository;

    @ParameterizedTest
    @ValueSource(strings = {"Civilization", "The Birth of a Nation", "The Blue Bird"})
    public void findByTitle(String title) {
        List<Movie> movies = movieRepository.findByTitle(title);
        assertFalse(movies.isEmpty());
        log.info("findByTitleLike ...");
        movies.forEach(movie -> log.info(movie.toString()));
    }


    @ParameterizedTest
    @ValueSource(strings = {"573a1390f29313caabcd5a93"})
    public void saveById(String id) {
        Optional<Movie> movieOpt = movieRepository.findById(id);
        assertFalse(movieOpt.isEmpty());
        log.info("findById ...");
        log.info(movieOpt.get().toString());

        Movie movie = movieOpt.get();
        Comment comment = new Comment();
        comment.setId(ObjectId.get());
        //Date date = new Date();
        //ObjectId objectIdDate = new ObjectId(date);
        comment.setText("nice movie");
        comment.setMovieId(movie.getId());
        commentRepository.save(comment);

        movie.setTitle("Civilization");
        movieRepository.save(movie);
    }


}
