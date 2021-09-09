from src import create_app, socket

app = create_app(debug=True)
app.app_context().push()

if __name__ == '__main__':
    print('in app py')
    socket.run(app, host='0.0.0.0')
