import 'package:flutter/material.dart';

class RoomPage1 extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Center(
      child: Scaffold(
        backgroundColor: Colors.grey[900],
        appBar: AppBar(
          title: Text(
            "DISPONÍVEL",
            style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 24
            ),
          ),
          backgroundColor: Colors.green,
        ),
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[
            Center(
              child: Image(
                  image: AssetImage('assets/images/CheckVerde.gif'),
                  width: 250
              ),
            ),
            Text(
              "A sala está disponível!",
              style: TextStyle(
                fontWeight: FontWeight.bold,
                color: Colors.white,
                fontSize: 16,
              ),
            ),
          ],
        ),
      ),
    );
  }
}