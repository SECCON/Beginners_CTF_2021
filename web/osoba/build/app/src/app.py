from flask import Flask, request, send_file, make_response

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    page = request.args.get('page', 'public/index.html')    
    response = make_response(send_file(page))
    response.content_type = "text/html"
    return response

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080)