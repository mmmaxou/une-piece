#ifndef SCORES_UP_HPP__
#define SCORES_UP_HPP__

#pragma once

#include <string>
#include <ctime>

namespace UP
{

/**
 * @brief Data structure for a SCORE
 * 
 */
class Score
{
public:
  /**
   * @brief Construct a new Score object
   * 
   * @param name 
   * @param score 
   * @param time
   */
  Score(const std::string &name, const int &score, const time_t time = std::time(0))
      : _name(name), _score(score), _time(time){};

  /**
   * @brief Getter of the name
   * 
   * @return const std::string 
   */
  inline const std::string name() const { return _name; };

  /**
   * @brief Getter of the score
   * 
   * @return const int 
   */
  inline const int score() const { return _score; };

  /**
   * @brief Getter of the time
   * 
   * @return const time_t 
   */
  inline const time_t time() const { return _time; };

  /**
   * @brief Getter of the name
   * 
   * @return const std::string 
   */
  inline std::string name() { return _name; };

  /**
   * @brief Getter of the score
   * 
   * @return int 
   */
  inline int score() { return _score; };

  /**
   * @brief Getter of the time
   * 
   * @return time_t 
   */
  inline time_t time() { return _time; };

  /**
   * @brief Set the Name object
   * 
   * @param n 
   */
  inline void setName(const std::string &n) { _name = n; };
  /**
   * @brief Set the Score object
   * 
   * @param s 
   */
  inline void setScore(const int &s) { _score = s; };
  /**
   * @brief Set the Time object
   * 
   * @param t 
   */
  inline void setTime(const time_t &t) { _time = t; };

  /**
   * @brief Compare two Scores, for a sorted map
   * 
   * @param s 
   * @return true 
   * @return false 
   */
  bool operator<(const Score &s) const
  {
    return _score > s._score;
  }

  /**
   * @brief Display a Score
   * 
   * @param os 
   * @param s 
   * @return std::ostream& 
   */
  friend std::ostream &operator<<(std::ostream &os, const Score &s)
  {
    char buffer[80];
    strftime(buffer, 80, "%R %D", localtime(&(s._time)));
    os << s._name << ": " << s._score << " | at : " << buffer;
  }

private:
  std::string _name;
  int _score;
  time_t _time;
};

} // namespace UP

#endif