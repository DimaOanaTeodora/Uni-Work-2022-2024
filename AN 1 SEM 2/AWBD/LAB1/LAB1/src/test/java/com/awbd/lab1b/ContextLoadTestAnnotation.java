package com.awbd.lab1b;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class ContextLoadTestAnnotation {

    @Test
    public void contructorDI(){
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext(SubscriptionConfig.class);

        Subscription myBooksSubscription = context.getBean("myBooksSubscription", Subscription.class);

        System.out.println(myBooksSubscription.getPrice() + " " + myBooksSubscription.getDescription());

        context.close();
    }

    @Test
    public void setterDI(){
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext(SubscriptionConfig.class);
        Subscription myMoviesSubscription = context.getBean("myMoviesSubscription", Subscription.class);
        System.out.println(myMoviesSubscription.getPrice() + " " + myMoviesSubscription.getDescription());

        context.close();
    }

    @Test
    public void propertyDITest(){
        AnnotationConfigApplicationContext context =
                new AnnotationConfigApplicationContext("com.awbd.lab1b");
        Subscription mySportSubscription = context.getBean("mySportSubscription", Subscription.class);
        System.out.println(mySportSubscription.getPrice() + " "
                + mySportSubscription.getDescription());
        context.close();
    }

}
