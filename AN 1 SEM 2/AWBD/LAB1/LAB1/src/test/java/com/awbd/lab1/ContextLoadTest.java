package com.awbd.lab1;

import org.junit.Test;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class ContextLoadTest {

    @Test
    public void testXmlContext(){

        // load the spring configuration file
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContext.xml");

        // retrieve bean from spring container
        Subscription mySportSubscription = context.getBean("mySportSubscription", Subscription.class);

        // call methods on the bean
        System.out.println(mySportSubscription.getPrice() + " " + mySportSubscription.getDescription());

        Subscription myBooksSubscription = context.getBean("myBooksSubscription", Subscription.class);

        // call methods on the bean
        System.out.println(myBooksSubscription.getPrice() + " " + myBooksSubscription.getDescription());

        Subscription myMoviesSubscription = context.getBean("myMoviesSubscription", Subscription.class);

        // call methods on the bean
        System.out.println(myMoviesSubscription.getPrice() + " " + myMoviesSubscription.getDescription());

        // close the context
        context.close();
    }

    @Test
    public void contructorDI(){
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContextDI.xml");

        Subscription theSubscription = context.getBean("myBooksSubscription", Subscription.class);

        System.out.println(theSubscription.getPrice() + " " + theSubscription.getDescription());

        context.close();
    }

    @Test
    public void setterDI(){
        ClassPathXmlApplicationContext context =
                new ClassPathXmlApplicationContext("applicationContextDI.xml");

        Subscription theSubscription = context.getBean("myMoviesSubscription", Subscription.class);

        System.out.println(theSubscription.getPrice() + " " + theSubscription.getDescription());

        context.close();
    }


}
