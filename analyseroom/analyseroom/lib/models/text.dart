import 'package:flutter/material.dart' show Colors, FontWeight, Text, TextAlign, TextStyle;
  
  Text buildText() {
    return Text(
              "Develop by Ana & Zoey",
              textAlign: TextAlign.center,
              style: TextStyle(
                  color: Colors.white,
                  fontWeight: FontWeight.bold,
                  letterSpacing: 3,
                  fontSize: 12,
              ),
            );
  }