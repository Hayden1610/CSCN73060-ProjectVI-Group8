from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class Course(db.Model):
    __bind_key__ = 'courses'
    id = db.Column(db.String(10), primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    professor_name = db.Column(db.String(100), nullable=False)

    def __repr__(self):
        return f'<Course {self.name}>'

class Student(db.Model):
    __bind_key__ = 'students'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    email = db.Column(db.String(100), nullable=False)

    def __repr__(self):
        return f'<Student {self.name}>'
