/**
 * HW1
 * Author: Bao Tran Tran Do
 * 1/16/2022
 */

import 'package:flutter/material.dart';
import 'package:hw1/pages/landing_page.dart';
import 'package:hw1/pages/sign_in_anonymously_page.dart';
import 'package:hw1/storage/storage.dart';
import 'package:provider/provider.dart';
import 'package:hw1/pages/home_page.dart';
import 'package:camera/camera.dart';
import 'package:firebase_core/firebase_core.dart';
//import 'firebase_options.dart';
/**
 * Main to run the program
 */
Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MyApp());

}

/**
 * The app layout design such as background colors and the banners
 */
class MyApp extends StatelessWidget {
  static final String title = 'HW: Bao Tran Do\'s Todo App';

  //final firstCamera;
  //MyApp({required this.firstCamera});




  @override
  Widget build(BuildContext context) => ChangeNotifierProvider(
    create: (context) => TodosStorage(),
    child: MaterialApp(
      home: LandingPage(),
      title: title,
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primarySwatch: Colors.blueGrey,
        scaffoldBackgroundColor: Color(0xFFFBE9E7),
      ),
    ),
  );


}

