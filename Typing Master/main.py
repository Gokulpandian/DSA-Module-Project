import random
import json
import time
import sys

def update_leaderboard(username, wpm):
    # Load existing leaderboard
    try:
        with open('leaderboard.json', 'r') as file:
            leaderboard = json.load(file)
    except FileNotFoundError:
        leaderboard = []

    # Add new entry
    leaderboard.append({'username': username, 'wpm': wpm})

    # Sort the leaderboard by WPM
    leaderboard = sorted(leaderboard, key=lambda x: x['wpm'], reverse=True)

    # Update leaderboard file
    with open('leaderboard.json', 'w') as file:
        json.dump(leaderboard, file, indent=4)

def show_leaderboard():
    try:
        with open('leaderboard.json', 'r') as file:
            leaderboard = json.load(file)

        print("\nLeaderboard:")
        for entry in leaderboard:
            print(f"{entry['username']} - {entry['wpm']} WPM")
    except FileNotFoundError:
        print("\nLeaderboard is empty.")

def load_words_from_json(category):
    try:
        with open(f'{category}_words.json', 'r') as file:
            words_data = json.load(file)
            return words_data['words']
    except FileNotFoundError:
        print(f"Error: Words file for '{category}' not found.")
        sys.exit()

def get_user_input():
    try:
        user_input = input("\nType the words exactly as shown (Ctrl + Q to quit): ")
        if user_input == '\x11':  # Ctrl + Q
            print("Exiting the game.")
            sys.exit()
        return user_input
    except KeyboardInterrupt:
        print("\nExiting the game.")
        sys.exit()

def main():
    print("Welcome to the Terminal Typing Master!")

    username = input("Enter your username: ")

    while True:
        print("\nOptions:")
        print("1. Start Typing Test")
        print("2. Show Leaderboard")
        print("3. Exit")

        choice = input("Select an option (1/2/3): ")

        if choice == '1':
            category = input("Choose a typing category: ")
            words = load_words_from_json(category)

            start_time = time.time()
            correct_words = 0

            for word in words:
                print(word)
                user_input = get_user_input()

                if user_input == word:
                    correct_words += 1

            end_time = time.time()
            total_time = end_time - start_time
            wpm = int((correct_words / total_time) * 60)

            print(f"\nTyping Test Results:")
            print(f"Words Typed: {correct_words}")
            print(f"Time Taken: {total_time:.2f} seconds")
            print(f"Words Per Minute (WPM): {wpm}")

            update_leaderboard(username, wpm)

        elif choice == '2':
            show_leaderboard()

        elif choice == '3':
            print("Exiting the game.")
            sys.exit()

        else:
            print("Invalid choice. Please choose a valid option.")

if __name__ == "__main__":
    main()

