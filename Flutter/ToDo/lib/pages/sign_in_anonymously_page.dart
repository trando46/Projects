import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';


/**
 * Class to sign in anonymously
 */
class SignInAnonymouslyPage extends StatelessWidget {

  Future<void> _signInAnonymously() async {
    try {
      // Try to sign in
      await FirebaseAuth.instance.signInAnonymously();
      print("[SUCCESS] Signed in with temporary account!");
    } catch (e) {
      // Print out the error message
      print("[ERROR] " + e.toString());
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Bao Tran Tran Do => HW5')),
      body: Center(
        child:
        TextButton(
          style: TextButton.styleFrom(
            foregroundColor: Colors.blue,
            textStyle: const TextStyle(fontSize: 35),
            backgroundColor: Colors.white,
          ),
          onPressed: _signInAnonymously,
          child: const Text('Sign in anonymously!'),
        ),
      ),
    );
  }
}