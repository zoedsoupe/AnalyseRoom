import 'package:flutter/material.dart';
import 'package:Analyseroom/models/roomPage1.dart';
import 'package:Analyseroom/models/roomPage2.dart';
import 'package:Analyseroom/Screens/loadingScreen.dart';
import 'package:firebase_database/firebase_database.dart';

class RoomPageBuilderFireBase extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: StreamBuilder<Event>(
        stream: FirebaseDatabase.instance.reference().child('db').child('id').onValue,
        builder: (BuildContext context, AsyncSnapshot<Event> event) {
          if (!event.hasData) {
            return LoadingScreen();
          }
          if(event.data.snapshot.value != 0) {
            return RoomPage2();
          } else return RoomPage1();
        },
      ),
    );
  }
}