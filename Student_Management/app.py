from flask import Flask
from models import db, Course, Student
import os

app = Flask(__name__)

# Database configuration
BASE_DIR = os.path.abspath(os.path.dirname(__file__))
DB_DIR = os.path.join(BASE_DIR, "database")
os.makedirs(DB_DIR, exist_ok=True)

# Use a single database file for both students and courses
app.config['SQLALCHEMY_DATABASE_URI'] = f'sqlite:///{os.path.join(DB_DIR, "school.db")}'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.secret_key = "your-secret-key"

# Initialize database
db.init_app(app)

from routes import init_app
init_app(app)

def initialize_database():
    with app.app_context():
        # Create all tables in the database
        db.create_all()
        
        # Add some sample data if the database is empty
        if not Course.query.first():
            sample_courses = [
                Course(id='CS101', name='Introduction to Computer Science', professor_name='Dr. Smith'),
                Course(id='MATH201', name='Advanced Mathematics', professor_name='Dr. Johnson')
            ]
            for course in sample_courses:
                db.session.add(course)
        
        if not Student.query.first():
            sample_students = [
                Student(name='John Doe', email='john@example.com'),
                Student(name='Jane Smith', email='jane@example.com')
            ]
            for student in sample_students:
                db.session.add(student)
        
        db.session.commit()

if __name__ == "__main__":
    initialize_database()
    app.run(debug=True)