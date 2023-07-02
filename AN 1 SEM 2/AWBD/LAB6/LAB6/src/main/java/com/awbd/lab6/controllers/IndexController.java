package com.awbd.lab6.controllers;

import com.awbd.lab6.domain.Movie;
import com.awbd.lab6.services.MovieService;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.mongodb.core.index.Index;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;
import java.util.Optional;

@Controller
public class IndexController {

    MovieService movieService;

    IndexController(MovieService movieService){
        this.movieService = movieService;
    }

    @RequestMapping({"", "/", "/index"})
    public String getIndexPage(Model model){
        List<Movie> movies = movieService.findAll();
        model.addAttribute("movies",movies);

        return "movieList";
    }


    @RequestMapping({"/movies"})
    public String getMoviePage(Model model,
                               @RequestParam("page") Optional<Integer> page,
                               @RequestParam("size") Optional<Integer> size) {
        int currentPage = page.orElse(1);
        int pageSize = size.orElse(5);

        Page<Movie> moviePage = movieService.findPaginated(PageRequest.of(currentPage - 1, pageSize));

        model.addAttribute("moviePage",moviePage);

        return "moviePaginated";
    }


}
