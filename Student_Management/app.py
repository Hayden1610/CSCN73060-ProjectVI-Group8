from flask import Flask
from models import db, Course, Student  # Insert models frist
import os

app = Flask(__name__)

# Database Link
BASE_DIR = os.path.abspath(os.path.dirname(__file__))
DB_DIR = os.path.join(BASE_DIR, "database")
os.makedirs(DB_DIR, exist_ok=True)

app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///:memory:'
app.config['SQLALCHEMY_BINDS'] = {
    'courses': f'sqlite:///{os.path.join(DB_DIR, "course.db")}',
    'students': f'sqlite:///{os.path.join(DB_DIR, "student.db")}',
}
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.secret_key = "your-secret-key"  


db.init_app(app)

from routes import init_app
init_app(app)

def initialize_databases():
    with app.app_context():
        engine_courses = db.engines['courses']
        engine_students = db.engines['students']
        if not os.path.exists(os.path.join(DB_DIR, "course.db")):
            print("Creating course.db")
            Course.metadata.create_all(engine_courses)
        if not os.path.exists(os.path.join(DB_DIR, "student.db")):
            print("Creating student.db")
            Student.metadata.create_all(engine_students)

if __name__ == "__main__":
    initialize_databases()
    app.run(debug=True)

