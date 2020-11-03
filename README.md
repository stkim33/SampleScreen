## SampleScreen 

### Language : C/C++(MFC)  
### IDE : visual studio 2015

#### Screen Program Initialization

```C
  func : CSampleScreenDlg::OnInitDialog()...
  
  //Screen Btn Init
  m_CtrlScreenBtn.m_Screen_1Ch.SetParam(this, E_SCREEN_1CH);
  m_CtrlScreenBtn.m_Screen_4Ch.SetParam(this, E_SCREEN_4CH);
  m_CtrlScreenBtn.m_Screen_9Ch.SetParam(this, E_SCREEN_9CH);
  m_CtrlScreenBtn.m_Screen_16Ch.SetParam(this, E_SCREEN_16CH);

  //Screen Object Init
  m_ScreenBase.ModifyStyle(0, WS_CLIPCHILDREN);
  m_ScreenBase.SetParam(this);
  m_ScreenBase.ScreenInit();
  m_pClickScreen = m_ScreenBase.ScreenChange(m_index);
```

####   Screen Object Allocation
```C
  func : CScreenbase::ScreenInit()..
  
  for (int i = 0; i < MAX_SCREEN_CNT; i++)
  {
    //new
    pScreenData = new PositionData;
    pScreenData->pScreenView = new CScreenView;
    pScreenData->pScreenHead = new CScreenHead;

    //pMain
    pScreenData->pScreenView->SetParam(m_pParent, this, i + 1);
    pScreenData->pScreenHead->SetParam(m_pParent, i + 1);

    //Create
    pScreenData->pScreenView->Create(IDD_SCREEN_VIEW, this);
    pScreenData->pScreenHead->Create(IDD_SCREEN_HEAD, this);

    //add
    m_listScreen.AddTail(pScreenData);
  }
```
![image](https://user-images.githubusercontent.com/52806386/98004510-60bb8700-1e33-11eb-8972-a346faf7f66b.png)
