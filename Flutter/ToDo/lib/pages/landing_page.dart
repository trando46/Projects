import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:hw1/pages/sign_in_anonymously_page.dart';
import 'package:hw1/pages/home_page.dart';

/***
 * This page will determine whether the user is signed in or not. If not signed
 * in will prompt them to click on the button to sign in
 */
class LandingPage extends StatelessWidget {

  @override
  Widget build(BuildContext context) {

    var state = FirebaseAuth.instance.authStateChanges();

    return StreamBuilder<User?>(

      // check the state
      stream: state,

      builder: (context, snapShot) {
        if (ConnectionState.active == snapShot.connectionState ) {

          // get the data of the user
          User? user = snapShot.data;
          print(user);

          if (user != null) {
            // if user is signed in then take them to the homepage
            return HomePage();
          }
          // no user signed in prompt them to sign in
          return SignInAnonymouslyPage();

          // When there is connection issues
        } else {
          return Scaffold(
              body: Column(
                children: [
                  Center(
                    child: Text("Having issues at the moment! Come back later"),
                  ),
                ],
              )
          );
        }

      },
    );
  }
}