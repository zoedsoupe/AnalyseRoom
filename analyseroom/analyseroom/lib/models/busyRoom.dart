import 'package:flutter/material.dart';
import 'package:Analyseroom/models/roomPage1.dart';
import 'package:firebase_database/firebase_database.dart';

class BusyRoom extends StatelessWidget {
  //final db = FirebaseDatabase.instance.reference().child('db');
  final id;
  BusyRoom(this.id);

  var name, enterTime, exitTime, lesson;

  Widget build(BuildContext context) {
    switch (id) {
      case 1: name = "Ana Laura";
              enterTime = "14:20";
              exitTime = "18:00";
              lesson = "Marketing II";
      break;
      case 2: name = "Zoey";
              enterTime = "18:20";
              exitTime = "22:00";
              lesson = "Programação I";
      break;
      case 3: name = "Renata Mesquita";
              enterTime = "8:00";
              exitTime = "12:00";
              lesson = "Projeto Final";
      break;
      default: return RoomPage1();
    }
    return Center(
      child: Scaffold(
        backgroundColor: Colors.grey[900],
        appBar: AppBar(
          title: Text(
            "INDISPONÍVEL",
            style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 24
            ),
          ),
          backgroundColor: Colors.red[800],
        ),
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[
            Text(
              "Professor: $name",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 16,
              ),
            ),
            Text(
              "Matéria: $lesson",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 16,
              ),
            ),
            Text(
              "Horário de início da aula: $enterTime",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 16,
              ),
            ),
            Text(
              "Horário de término da aula: $exitTime",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 16,
              ),
            ),
            Center(
              child: Image(
                  image: AssetImage('assets/images/sala.png'),
                  width: 250
              ),
            ),
          ],
        ),
      ),
    );
  }
}