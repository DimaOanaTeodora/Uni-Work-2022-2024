package com.awbd.lab3a.lab3a.controller;

import com.awbd.lab3a.lab3a.domain.Movie;
import com.awbd.lab3a.lab3a.service.MovieService;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

@RestController
@RequestMapping("movies")
public class MovieController {

    MovieService movieService;

    public MovieController(MovieService movieService) {
        this.movieService = movieService;
    }

    @GetMapping("/{id}")
    public Mono<Movie> findMovie(@PathVariable String id){
        return movieService.findById(id)
                .defaultIfEmpty(new Movie("0"));
    }

    @GetMapping("")
    public Flux<Movie> moviesAll() {
        return movieService.findAll();
    }

    @GetMapping(value = "/stream", produces = MediaType.TEXT_EVENT_STREAM_VALUE)
    public Flux<Movie> moviesAllStream() {

        return movieService.findAll();
    }
}
