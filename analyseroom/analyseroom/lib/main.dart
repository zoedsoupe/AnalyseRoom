import 'package:Analyseroom/Screens/homepage.dart';
import 'package:flutter/material.dart';


void main() {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(AnalyseRoom());
}

class AnalyseRoom extends StatelessWidget {

  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        primaryColor: Colors.grey[900],
        accentColor: Colors.grey[850],
        canvasColor: Colors.grey[850]
      ),
      home: HomePage(),
    );
  }
}

