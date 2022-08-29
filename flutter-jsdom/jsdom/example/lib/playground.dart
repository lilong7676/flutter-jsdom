import 'package:flutter/material.dart';

import 'package:jsdom/jsdom.dart';

class Playground extends StatefulWidget {
  const Playground({Key? key}) : super(key: key);

  @override
  State<Playground> createState() => _PlaygroundState();
}

class _PlaygroundState extends State<Playground> {
  late TextEditingController _controller;
  final _jsdomPlugin = Jsdom();

  @override
  void initState() {
    super.initState();
    _controller = TextEditingController();
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

  void runCode() {
    String inputValue = _controller.text;
    _jsdomPlugin.executeJavascript(inputValue);
  }

  @override
  Widget build(BuildContext context) {
    return Column(crossAxisAlignment: CrossAxisAlignment.start, children: [
      Padding(
        padding: const EdgeInsets.all(16),
        child: TextField(
          controller: _controller,
          maxLines: 20,
          decoration: const InputDecoration(
              hintText: "请输入js",
              border: OutlineInputBorder(borderSide: BorderSide()),
              contentPadding: EdgeInsets.all(15)),
          onSubmitted: (String value) async {
            await showDialog<void>(
              context: context,
              builder: (BuildContext context) {
                return AlertDialog(
                  title: const Text('Thanks!'),
                  content: Text(
                      'You typed "$value", which has length ${value.characters.length}.'),
                  actions: <Widget>[
                    TextButton(
                      onPressed: () {
                        Navigator.pop(context);
                      },
                      child: const Text('OK'),
                    ),
                  ],
                );
              },
            );
          },
        ),
      ),
      TextButton(onPressed: runCode, child: Text('run in quickjs')),
    ]);
  }
}
