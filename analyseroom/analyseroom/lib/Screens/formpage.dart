import 'package:Analyseroom/Screens/homepage.dart';
import 'package:flutter/material.dart';
import 'package:Analyseroom/models/sizeConfig.dart';
import 'package:flutter_email_sender/flutter_email_sender.dart';
import 'package:flutter_masked_text/flutter_masked_text.dart';

class FormPage extends StatefulWidget {
  @override
  _FormPageState createState() => _FormPageState();
}

class _FormPageState extends State<FormPage> {

  TextEditingController _numberCon = new MaskedTextController(mask: '(00)00000-0000');
  TextEditingController _nameCon = new TextEditingController();

  final GlobalKey<FormState> _formKeyValue = new GlobalKey<FormState>();
  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();

  Future<void> send() async {
    final Email email = Email(
      body: 'Nome: ' + _nameCon.text + '\n\n' +
            'Celular: ' + _numberCon.text + '\n\n' +
            'Descreva o erro obtido: \n  ',
      subject: 'Erro no aplicativo',
      recipients: ['zoey.spessanha@zeetech.io', 'a.laura.alves@gmail.com'],
    );

    String platformResponse;

    try {
      await FlutterEmailSender.send(email);
      platformResponse = 'O email foi enviado com sucesso!';
    } catch (error) {
      platformResponse = error.toString();
    }

    if (!mounted) return;

    _scaffoldKey.currentState.showSnackBar(SnackBar(
      content: Text(platformResponse),
    ));
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
        backgroundColor: Colors.grey[900],
        body: Form(
          key: _formKeyValue,
          autovalidate: true,
          child: new ListView(
            padding: const EdgeInsets.symmetric(horizontal: 15.0),
            children: <Widget>[
              SizedBox(height: SizeConfig.screenHeight / 3.5),
              new TextFormField(
                controller: _numberCon,
                decoration: const InputDecoration(
                  icon: const Icon(
                    Icons.phone,
                    color: Colors.white,
                  ),
                  hintStyle: TextStyle(color: Colors.white),
                  hintText: 'DDD + número',
                  labelStyle: TextStyle(color: Colors.white),
                  labelText: 'Celular',
                ),
                keyboardType: TextInputType.number,
                style: TextStyle(color: Colors.white),
              ),
              new TextFormField(
                textCapitalization: TextCapitalization.words,
                controller: _nameCon,
                decoration: const InputDecoration(
                  icon: const Icon(
                    Icons.account_circle,
                    color: Colors.white,
                  ),
                  hintStyle: TextStyle(color: Colors.white),
                  labelStyle: TextStyle(color: Colors.white),
                  hintText: 'Nome e sobrenome',
                  labelText: 'Nome',
                ),
                style: TextStyle(color: Colors.white),
              ),
              SizedBox(height: SizeConfig.screenHeight / 10),
              Column(
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: <Widget>[
                  RaisedButton(
                      color: Colors.white,
                      textColor: Colors.black,
                      child: Padding(
                          padding: EdgeInsets.all(10.0),
                          child: Row(
                            mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                            children: <Widget>[
                              Text("Enviar", style: TextStyle(fontSize: 20.0)),
                            ],
                          )),
                      onPressed: () {
                        //_nameCon.clear();
                        //_numberCon.clear();
                        send();
                        Navigator.pop(
                            context,
                            MaterialPageRoute(
                                builder: (context) => HomePage()
                            )
                        );
                      },
                      shape: new RoundedRectangleBorder(
                          borderRadius: new BorderRadius.circular(30.0))),
                ],
              ),
            ],
          ),
        )
      );
  }
}