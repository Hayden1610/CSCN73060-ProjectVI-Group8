// Add active class to current page link
document.addEventListener('DOMContentLoaded', function() {
    const currentPath = window.location.pathname;
    const navLinks = document.querySelectorAll('.nav a');
    navLinks.forEach(link => {
        if (link.getAttribute('href') === currentPath) {
            link.classList.add('active');
        }
    });
});

document.addEventListener("DOMContentLoaded", () => {
    const addCourseButton = document.getElementById("add-course-btn");
    const editButtons = document.querySelectorAll(".edit-btn");
    const modal = document.getElementById("edit-modal");
    const courseIdInput = document.getElementById("modal-course-id");
    const courseNameInput = document.getElementById("modal-course-name");
    const professorNameInput = document.getElementById("modal-professor-name");
    const updateButton = document.getElementById("update-btn");
    const deleteButton = document.getElementById("delete-btn");
    const cancelButton = document.getElementById("cancel-btn");

    // Add course logic
    addCourseButton.addEventListener("click", () => {
        const courseId = prompt("Enter Course ID:");
        const courseName = prompt("Enter Course Name:");
        const professorName = prompt("Enter Professor Name:");

        if (courseId && courseName && professorName) {
            fetch("/edit_course", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                    action: "add",
                    course_id: courseId,
                    course_name: courseName,
                    professor_name: professorName,
                }),
            })
                .then((res) => res.json())
                .then((data) => {
                    if (data.success) {
                        alert("Course added successfully!");
                        location.reload();
                    } else {
                        alert(data.error || "An error occurred.");
                    }
                });
        } else {
            alert("All fields are required.");
        }
    });

    // Edit course logic
    editButtons.forEach((button) => {
        button.addEventListener("click", (e) => {
            courseIdInput.value = e.target.dataset.id;
            courseNameInput.value = e.target.dataset.name;
            professorNameInput.value = e.target.dataset.professor;
            modal.classList.remove("hidden");
        });
    });

    // Update course logic
    updateButton.addEventListener("click", () => {
        const courseId = courseIdInput.value;
        const courseName = courseNameInput.value;
        const professorName = professorNameInput.value;

        if (courseName && professorName) {
            fetch("/edit_course", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                    action: "update",
                    course_id: courseId,
                    course_name: courseName,
                    professor_name: professorName,
                }),
            })
                .then((res) => res.json())
                .then((data) => {
                    if (data.success) {
                        alert("Course updated successfully!");
                        location.reload();
                    } else {
                        alert(data.error || "An error occurred.");
                    }
                });
        } else {
            alert("All fields are required.");
        }
    });

    // Delete course logic
    deleteButton.addEventListener("click", () => {
        const courseId = courseIdInput.value;

        if (confirm("Are you sure you want to delete this course?")) {
            fetch("/edit_course", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({ action: "delete", course_id: courseId }),
            })
                .then((res) => res.json())
                .then((data) => {
                    if (data.success) {
                        alert("Course deleted successfully!");
                        location.reload();
                    } else {
                        alert(data.error || "An error occurred.");
                    }
                });
        }
    });

    // Close modal
    cancelButton.addEventListener("click", () => {
        modal.classList.add("hidden");
    });
});

document.addEventListener("DOMContentLoaded", () => {
    // Function to update a student (PUT)
    async function updateStudent(id, data) {
        const response = await fetch(`/api/students/${id}`, {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(data)
        });
        return response.json();
    }

    // Function to partially update a student (PATCH)
    async function patchStudent(id, data) {
        const response = await fetch(`/api/students/${id}`, {
            method: 'PATCH',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(data)
        });
        return response.json();
    }

    // Function to delete a student (DELETE)
    async function deleteStudent(id) {
        const response = await fetch(`/api/students/${id}`, {
            method: 'DELETE',
        });
        return response.json();
    }

    // Function to get allowed methods for students (OPTIONS)
    async function getStudentOptions() {
        const response = await fetch('/api/students', {
            method: 'OPTIONS'
        });
        return response.json();
    }

    // Example usage
    const studentId = 1; // Replace with actual student ID
    const updateData = { name: 'Updated Name', email: 'updated@example.com' };
    const patchData = { email: 'newemail@example.com' };

    // Update a student
    updateStudent(studentId, updateData)
        .then(data => console.log(data))
        .catch(error => console.error(error));

    // Partially update a student
    patchStudent(studentId, patchData)
        .then(data => console.log(data))
        .catch(error => console.error(error));

    // Delete a student
    deleteStudent(studentId)
        .then(data => console.log(data))
        .catch(error => console.error(error));

    // Get allowed methods for students
    getStudentOptions()
        .then(data => console.log(data))
        .catch(error => console.error(error));
});