#ifndef _UI_H_
#define _UI_H_

#include "ChessBoard.h"

#include <final/final.h>

#include <string>
#include <iostream>
#include <sstream>

class RecordView: public finalcut::FTextView
{
public:
    explicit RecordView(finalcut::FWidget* parent=nullptr):
        FTextView(parent)
    {
    }
    ~RecordView()
    {
    }
    void appendStr(std::string str);
    inline bool scrollable()
    {
        return getRows() > getHeight() - 2;
    }
    inline void scrollBottom()
    {
        if (scrollable())
            scrollToY(getRows() - getHeight() + 2);
        return;
    }
protected:
    virtual void onKeyPress(finalcut::FKeyEvent* ev) override;
    virtual void onWheel(finalcut::FWheelEvent* ev) override;
};

class View: public finalcut::FDialog
{
public:
    inline static std::string coordStr(int r, int c)
    {
        return std::string(1, c + 'A') + std::string(1, ChessBoard::ROW - 1 - r + '1');
    }
    inline static int normalize(int x)
    {
        return (x + ChessBoard::ROW) % ChessBoard::ROW;
    }
public:
    explicit View(finalcut::FWidget* parent=nullptr);
    ~View();
protected:
    virtual void draw() override;
    virtual void onKeyPress(finalcut::FKeyEvent* ev) override;
    virtual void onWindowRaised(finalcut::FEvent* ev) override;
    virtual void onWindowActive(finalcut::FEvent* ev) override;
    virtual void onClose(finalcut::FCloseEvent* ev) override;
private:
    inline void cleanStream()
    {
        m_istr.str("");
        m_istr.clear();
    }
private:
    void changePieceColor(int r, int c, int select=UNSELECTED);
    void focusPiece(int r, int c);
    void selectPiece(int r, int c);
    bool load(bool msg=true);
    void restart();
    bool submit(void);
    void promote(std::string type);
public:
    static const int PIECE_NUM = 6;
    static const int PAWN = 0, ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5;
    static const int WIDTH = 7, HEIGHT = 3;
    static const int STYLE_NUM = 2;
    static const char* PIECE[STYLE_NUM][PIECE_NUM][ChessBoard::SIDE];
    static const char* PIECE_NULL;
    static const char* PIECE_UNKNOWN;
    static const char* COORD_ROW[ChessBoard::ROW];
    static const char* COORD_COL[ChessBoard::COL];
    static const char* HELP;
    static const char* STATUS_BAR;
    static const int UNSELECTED = 0, SELECTED = 1, FOCUSED = 2;
    static const int STATUS_NUM = 4;
    static const std::pair<const char*, int> STATUS[STATUS_NUM];
private:
    finalcut::FStatusBar* m_bar;
    finalcut::FLabel* m_coord_row[ChessBoard::ROW];
    finalcut::FLabel* m_coord_col[ChessBoard::COL];
    finalcut::FLabel* m_pieces[ChessBoard::ROW][ChessBoard::COL];
    finalcut::FLabel* m_selection_label;
    finalcut::FLabel* m_selection_coord;
    finalcut::FLabel* m_selection;
    finalcut::FLabel* m_status_label;
    finalcut::FLabel* m_status_player;
    finalcut::FLabel* m_status_state;
    finalcut::FLabel* m_record_label;
    RecordView* m_record;
    std::stringstream m_istr;
    int m_focus_r, m_focus_c;
    int m_select_r, m_select_c;
    int m_style;
    ChessBoard* m_board;
};

void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);

class PromotionView: public finalcut::FDialog
{
    friend void promotionSetValue(finalcut::FWidget* w, finalcut::FWidget::data_ptr data);
public:
    PromotionView(finalcut::FWidget* parent=nullptr);
    ~PromotionView();
    inline std::string getType()
    {
        return m_type;
    }
private:
    std::string m_type;
    finalcut::FButton* m_queen;
    finalcut::FButton* m_rook;
    finalcut::FButton* m_knight;
    finalcut::FButton* m_bishop;
};

#endif