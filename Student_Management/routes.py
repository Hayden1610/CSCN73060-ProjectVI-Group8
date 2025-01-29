from flask import render_template
from . import db
from .models import User

def init_app(app):
    @app.route('/')
    def index():
        users = User.query.all()
        return render_template('index.html', users=users)